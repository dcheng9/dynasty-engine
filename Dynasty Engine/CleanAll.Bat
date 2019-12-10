
rmdir /S /Q Debug
rmdir /S /Q Release

del /F /S *.sdf
del /F /S /A:H *.suo

rmdir /S /Q src\Debug
rmdir /S /Q src\Release

