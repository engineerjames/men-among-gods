// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

use serde::{Deserialize, Serialize};
use std::{path::PathBuf, process::Command, sync::Mutex};
use tauri::State;

#[derive(Serialize, Deserialize, Default, Debug)]
struct PlayerData {
    name: String,
    desc: String,
    pass: String,
    race: u8,
    sex: u8,
}

#[derive(Serialize, Deserialize, Default, Debug)]
struct ServerData {
    ip_address: String,
    port: String,
}

#[derive(Default)]
struct DataFromUI {
    player_data: Mutex<PlayerData>,
    server_data: Mutex<ServerData>,
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

#[tauri::command]
fn set_player_data(
    name: &str,
    pass: &str,
    desc: &str,
    sex: u8,
    race: u8,
    state: State<DataFromUI>,
) {
    let data_from_ui = PlayerData {
        name: name.to_owned(),
        pass: pass.to_owned(),
        desc: desc.to_owned(),
        race: race,
        sex: sex,
    };

    *state.player_data.lock().unwrap() = data_from_ui;
}

#[tauri::command]
fn set_server_data(ip_address: &str, port: &str, state: State<DataFromUI>) {
    let server_data = ServerData {
        ip_address: ip_address.to_owned(),
        port: port.to_owned(),
    };

    *state.server_data.lock().unwrap() = server_data;
}

// Learn more about Tauri commands at https://tauri.app/v1/guides/features/command
#[tauri::command]
fn play(state: State<DataFromUI>) {
    let player_data = state.player_data.lock().unwrap();
    let server_data = state.server_data.lock().unwrap();

    println!("Player Data: {:?}", player_data);
    println!("Server Data: {:?}", server_data);

    let exe_path = get_mag_client(std::env::current_exe().unwrap());

    println!("Running Men Among Gods client at: {}", exe_path.display());

    let stringified_player_data = serde_json::to_string(&(*player_data)).unwrap();
    let stringified_server_data = serde_json::to_string(&(*server_data)).unwrap();

    println!(
        "Stringified player data representation: {}",
        &stringified_player_data
    );
    println!(
        "Stringified server data representation: {}",
        &stringified_server_data
    );

    if cfg!(target_os = "windows") {
        Command::new(exe_path.clone())
            .args([
                "newentry",
                &stringified_player_data,
                &stringified_server_data,
            ])
            .current_dir(exe_path.parent().unwrap())
            .spawn()
            .expect("Command failed to start");
    } else {
        Command::new(exe_path.clone())
            .args([
                "newentry",
                &stringified_player_data,
                &stringified_server_data,
            ])
            .current_dir(exe_path.parent().unwrap())
            .spawn()
            .expect("Command failed to start");
    };
}

fn main() {
    tauri::Builder::default()
        .manage(DataFromUI::default())
        .invoke_handler(tauri::generate_handler![
            play,
            set_server_data,
            set_player_data
        ])
        .run(tauri::generate_context!())
        .expect("error while running tauri application");
}
