cmake --build C:/git/men-among-gods/out/build/MSVC-vcpkg-release --parallel 22 --target create_release
mkdir -p ./src/tauri_frontend/resources
# cp -R ./out/ <-- Get Build directory
cd ./src/tauri_frontend
pnpm run tauri build