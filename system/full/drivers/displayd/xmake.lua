target("displayd")
    set_type("application")
    add_deps("libdisplay", "libfont", , "libgraph", "libsconf")
    add_files("**.c")        
    install_dir("drivers")
target_end()
