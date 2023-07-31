// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use serde::{Deserialize, Serialize};
use std::{path::PathBuf, process::Command};

#[derive(Serialize, Deserialize)]
struct UIData {
    name: String,
    desc: String,
    pass: String,
    race: u8,
    sex: u8,
}

fn get_mag_client(main_exe_path: PathBuf) -> PathBuf {
    let main_dir = main_exe_path.parent().unwrap();

    let mag_client_name = "MenAmongGods.exe";

    let mag_client_path = main_dir
        .join("_up_")
        .join("resources")
        .join(mag_client_name);

    return mag_client_path;
}

// Learn more about Tauri commands at https://tauri.app/v1/guides/features/command
#[tauri::command]
fn play(name: &str, pass: &str, desc: &str, sex: u8, race: u8) {
    println!("Playing with {}, and {}", name, pass);
    let exe_path = get_mag_client(std::env::current_exe().unwrap());

    println!("Running Men Among Gods client at: {}", exe_path.display());

    let data_from_ui = UIData {
        name: name.to_owned(),
        pass: pass.to_owned(),
        desc: desc.to_owned(),
        race: race,
        sex: sex,
    };

    let stringified_data = serde_json::to_string(&data_from_ui).unwrap();

    println!("Stringified data representation: {}", &stringified_data);

    if cfg!(target_os = "windows") {
        Command::new(exe_path.clone())
            .args([
                "newentry",
                &stringified_data,
            ])
            .current_dir(exe_path.parent().unwrap())
            .spawn()
            .expect("Command failed to start");
    } else {
        Command::new(exe_path.clone())
            .args([
                "newentry",
                &stringified_data,
            ])
            .current_dir(exe_path.parent().unwrap())
            .spawn()
            .expect("Command failed to start");
    };
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![play])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
