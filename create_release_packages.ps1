cmake --build C:/git/men-among-gods/out/build/MSVC-vcpkg-release --parallel 22 --target create_release
New-Item -Force -Type Directory src/tauri_frontend/resources
Copy-Item -Force -Recurse ./out/build/MSVC-vcpkg-release/client_files/* src/tauri_frontend/resources
Set-Location -Path ./src/tauri_frontend
pnpm run tauri build
Set-Location -Path ../../