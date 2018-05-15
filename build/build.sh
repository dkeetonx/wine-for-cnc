#!/bin/sh
set -x

cd wine-win32-static/
rm -f ../wined3d/*

env PATH=$PATH:/home/dkeeton/repos/mxe/usr/bin/ ../../configure --without-x --without-freetype CFLAGS="-O2 -DWINE_NOWINSOCK -DUSE_WIN32_OPENGL" --with-wine-tools=../wine-tools/ LDFLAGS=" -static-libgcc" --host=i686-w64-mingw32.static
env PATH=$PATH:/home/dkeeton/repos/mxe/usr/bin/ gmake dlls/wined3d dlls/ddraw dlls/d3d8 dlls/d3d9 dlls/d3d10 dlls/d3d10core dlls/d3d11 dlls/dxgi dlls/d3d10_1

cp libs/wine/libwine.dll dlls/wined3d/wined3d.dll dlls/ddraw/ddraw.dll ../wined3d/
cd ../

tar -cJvf wined3d-dkeeton.txz wined3d

