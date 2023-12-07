target("powerd")
    set_type("application")
    add_deps("libbsp")
    add_files("**.c")        
    add_includedirs("include")
    install_dir("drivers/raspix")
    add_linkdirs("lib")
    add_ldflags("-lcsud", {force = true})
target_end()