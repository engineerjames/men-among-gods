New-Item -Force -Type Directory src/tauri_frontend/resources
Copy-Item -Force -Recurse ./out/build/MSVC-vcpkg-debug/client_files/* src/tauri_frontend/resources
Set-Location -Path ./src/tauri_frontend
pnpm run tauri build