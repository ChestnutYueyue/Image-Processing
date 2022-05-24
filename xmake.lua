add_rules("mode.debug","mode.release")
add_requires("opencv")

target("image_processing")
    add_rules("qt.widgetapp")
    add_files("src/**.cpp")
    add_files("src/**.ui")
    add_files("src/**.h")
    add_packages("opencv")