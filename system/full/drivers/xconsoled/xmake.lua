target("xconsoled")
    set_type("application")
    add_deps("libgraph","libttf","libfont","libhash", "libupng","libx++", "libx","libsconf", "libcxx")
    add_files("**.cc")        
    install_dir("drivers")
target_end()