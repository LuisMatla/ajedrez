{
    "cmd": ["gcc", "$file_name", "-I", "C:\\freeglut\\include", "-L", "C:\\freeglut\\lib", "-w", "-Wl,-subsystem,windows", "-lopengl32", "-lglu32", "-lfreeglut", "-o", "$file_base_name.exe"],
    "working_dir": "${project_path}",
    "selector": ["source.c"],
    "shell": true
}
 