#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <stdio.h>
#include <ewoksys/vfs.h>
#include <ewoksys/core.h>
#include <ewoksys/ipc.h>
#include <ewoksys/proc.h>

#include <ewoksys/mstr.h>
#include <fcntl.h>
#include <ewoksys/klog.h>
#include <ewoksys/syscall.h>
#include "shell.h"

static int cd(const char* dir) {
	char cwd[FS_FULL_NAME_MAX];
	if(getcwd(cwd, FS_FULL_NAME_MAX-1) == NULL)
		return -1;
	if(strcmp(dir, ".") == 0)
		return 0;
	while(*dir == ' ') /*skip all space*/
		dir++;
	if(dir[0] == 0) {
		chdir("/");
		return 0;
	}

	if(strcmp(dir, "..") == 0) {
		if(strcmp(cwd, "/") == 0)
			return 0;

		int len = strlen(cwd)  - 1;
		for(int i=len; i>=0; i--) {
			if(cwd[i] == '/') {
				cwd[i] = 0;
				break;
			}
		}
		if(cwd[0] == 0) {
			chdir("/");
			return 0;
		}
	}
	else if(dir[0] == '/') {
		strcpy(cwd, dir);
	}
	else {
		int len = strlen(cwd);
		if(cwd[len-1] != '/') {
			cwd[len] = '/';
			len++;
		}
		strcpy(cwd+len, dir);
	}

	fsinfo_t info;
	if(vfs_get_by_name(cwd, &info) != 0)
		printf("[%s] not exist!\n", dir);	
	else if(info.type != FS_TYPE_DIR)
		printf("[%s] is not a directory!\n", dir);	
	else if(chdir(cwd) != 0) {
		if(errno == ENOENT)
			printf("[%s] not exist!\n", dir);	
		else if(errno == EPERM)
			printf("[%s] access denied!\n", dir);	
		else
			printf("[%s] denied!\n", dir);	
	}
	return 0;
}

static void export_all(void) {
	proto_t out;
	PF->init(&out);
	int core_pid = syscall0(SYS_CORE_PID);
	int res = ipc_call(core_pid, CORE_CMD_GET_ENVS, NULL, &out);
	if(res != 0) {
		PF->clear(&out);
		return;
	}
		
	int n = proto_read_int(&out);
	if(n > 0) {
		for(int i=0; i<n; i++) {
			const char* name = proto_read_str(&out);
			const char* value = proto_read_str(&out);
			printf("declare -x %s=%s\n", name, value);
		}
	}
	PF->clear(&out);
}

static void export_get(const char* arg) {
	const char* value = getenv(arg);
	if(value == NULL)
		value = "";
	printf("%s=%s\n", arg, value);
}

static void export_set(const char* arg) {
	char name[64] = {0};
	char* v = strchr(arg, '=');
	if(v == NULL)
		return;
	int len = v-arg;
	strncpy(name, arg, len < 64 ? len : 63);
	setenv(name, (v+1));
}

static int export(const char* arg) {
	char* v = strchr(arg, '=');
	if(v == NULL)
		export_get(arg);
	else
		export_set(arg);
	return 0;
}

static int history(void) {
	old_cmd_t* oc = _history_tail;
	while(oc != NULL) {
		printf("%s\n", oc->cmd->cstr);
		oc = oc->prev;
	}
	return 0;
}

static int set_stdio(const char* dev) {
	while(*dev == ' ' || *dev == '\t') /*skip all space*/
		dev++;

	int fd = open(dev, O_RDWR);
	if(fd > 0) {
		dup2(fd, 0);
		dup2(fd, 1);
		dup2(fd, 2);
		dup2(fd, VFS_BACKUP_FD0);
		dup2(fd, VFS_BACKUP_FD1);
		close(fd);
		setenv("CONSOLE_ID", dev);
		return 0;
	}
	return -1;
}

int32_t handle_shell_cmd(const char* cmd) {
	if(strcmp(cmd, "exit") == 0) {
		_terminated = true;
		return 0;
	}
	else if(strcmp(cmd, "cd") == 0) {
		const char* home = getenv("HOME");
		if(home == NULL || home[0] == 0)
			home = "/";
		return cd(home);
	}
	else if(strncmp(cmd, "cd ", 3) == 0) {
		return cd(cmd + 3);
	}
	else if(strcmp(cmd, "export") == 0) {
		export_all();
		return 0;
	}
	else if(strncmp(cmd, "export ", 7) == 0) {
		return export(cmd+7);
	}
	else if(strcmp(cmd, "history") == 0) {
		return history();
	}
	else if(strncmp(cmd, "set_stdio ", 10) == 0) {
		return set_stdio(cmd+10);
	}
	return -1; /*not shell internal command*/
}
