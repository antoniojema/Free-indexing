# Localizamos los archivos de codigo
set(
    HeaderList
    ""
)

set(
    SRCList
    "box_test.cpp"
    "log_test.cpp"
    "NDContainer_test.cpp"
)

set(
    ExtraList
    ""
)

set(CML "CMakeLists.txt")

CreateGTestTarget()
