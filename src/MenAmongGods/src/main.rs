#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")] // hide console window on Windows in release

use eframe::egui;
use notify::{RecommendedWatcher, RecursiveMode, Config, Watcher};
use serde_json::json;
use std::fs;
use std::path::Path;
use std::process::Command;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Mutex;
use std::thread::{self};
use tinyfiledialogs::{MessageBoxIcon, YesNo};

static SHOULD_RESET_UI: AtomicBool = AtomicBool::new(false);
static LOADED_JSON: Mutex<serde_json::Value> = Mutex::new(serde_json::Value::Null);
static HAS_LOADED_MOA: AtomicBool = AtomicBool::new(false);
static LOADED_MOA_PATH: Mutex<String> = Mutex::new(String::new());

fn watch<P: AsRef<Path>>(path: P) -> notify::Result<()> {
    let (tx, rx) = std::sync::mpsc::channel();

    // Automatically select the best implementation for your platform.
    // You can also access each implementation directly e.g. INotifyWatcher.
    let mut watcher = RecommendedWatcher::new(tx, Config::default())?;

    // Add a path to be watched. All files and directories at that path and
    // below will be monitored for changes.
    watcher.watch(path.as_ref(), RecursiveMode::NonRecursive)?;

    for res in rx {
        match res {
            Ok(event) => println!("changed: {:?}", event),
            Err(e) => println!("watch error: {:?}", e),
        }
    }

    Ok(())
}

fn main() -> Result<(), eframe::Error> {
    env_logger::init(); // Log to stderr (if you run with `RUST_LOG=debug`).
    let options = eframe::NativeOptions {
        initial_window_size: Some(egui::vec2(400.0, 300.0)),
        ..Default::default()
    };

    eframe::run_native(
        "Men Among Gods", // TODO: Include version information
        options,
        Box::new(|_cc| Box::<MyApp>::default()),
    )
}

#[derive(PartialEq, Clone, Copy)]
enum Sex {
    Male = 1,
    Female = 2,
}

#[derive(PartialEq, Clone, Copy)]
enum Race {
    Templar = 1,
    Mercenary = 3,
    Harakim = 2,
}

struct MyApp {
    name: String,
    description: String,
    sex: Sex,
    race: Race,
    password: String,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            name: "".to_owned(),
            description: "".to_owned(),
            sex: Sex::Male,
            race: Race::Templar,
            password: "".to_owned(),
        }
    }
}

fn get_reset_choice() -> YesNo {
    let choice = tinyfiledialogs::message_box_yes_no(
        "Reset entries?",
        "WARNING: Selecting yes will erase the player data held within the UI.  
        \nInsure you have saved your player files first.\n\nSelect yes to reset the UI.",
        MessageBoxIcon::Warning,
        YesNo::No,
    );

    return choice;
}

fn get_json_body_for_client(app: &MyApp) -> String {
    let race = app.race as u8;
    let sex = app.sex as u8;

    json!({
        "name": app.name,
        "desc": app.description,
        "pass": app.password,
        "race": race,
        "sex" : sex,
    })
    .to_string()
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Character Details");

            ui.vertical(|ui| {
                let name_label = ui.label("Name: ");
                ui.text_edit_singleline(&mut self.name)
                    .labelled_by(name_label.id);
            });

            ui.vertical(|ui| {
                let password_label = ui.label("Password: ");

                ui.add(egui::widgets::TextEdit::singleline(&mut self.password).password(true))
                    .labelled_by(password_label.id);
            });

            ui.label("Sex");
            ui.horizontal(|ui| {
                ui.radio_value(&mut self.sex, Sex::Male, "Male");
                ui.radio_value(&mut self.sex, Sex::Female, "Female");
            });

            ui.label("Race: ");
            ui.horizontal(|ui| {
                ui.radio_value(&mut self.race, Race::Templar, "Templar");
                ui.radio_value(&mut self.race, Race::Mercenary, "Mercenary");
                ui.radio_value(&mut self.race, Race::Harakim, "Harakim");
            });

            let desc_label = ui.label("Description: ");
            ui.add(egui::widgets::TextEdit::multiline(&mut self.description))
                .labelled_by(desc_label.id);

            ui.horizontal(|ui| {
                if ui.button("Play").clicked() {
                    if cfg!(target_os = "windows") {
                        Command::new("cmd")
                            .args(["/C", "echo hello"])
                            .output()
                            .expect("failed to execute process");
                    } else {
                        let json_arg = get_json_body_for_client(&self);
                        let file_path = LOADED_MOA_PATH.lock().unwrap().clone();

                        if HAS_LOADED_MOA.load(Ordering::Relaxed) == true {
                            Command::new(
                                "/home/james/git/men-among-gods/build/src/new_client/MenAmongGods",
                            ) // TODO: Don't hard-code this
                            .arg("moafile")
                            .arg(file_path)
                            .arg(self.password.clone())
                            .output()
                            .expect("failed to execute process");
                        } else {
                            Command::new(
                                "/home/james/git/men-among-gods/build/src/new_client/MenAmongGods",
                            ) // TODO: Don't hard-code this
                            .arg("newentry")
                            .arg(json_arg)
                            .output()
                            .expect("failed to execute process");
                        }
                    }
                }
                if ui.button("New").clicked() {
                    HAS_LOADED_MOA.store(false, Ordering::Relaxed);

                    thread::spawn(move || {
                        let choice = get_reset_choice();

                        match choice {
                            YesNo::No => (),
                            YesNo::Yes => SHOULD_RESET_UI.store(true, Ordering::Relaxed),
                        };
                    });
                }

                if ui.button("Load").clicked() {
                    let open_file: String;
                    match tinyfiledialogs::open_file_dialog(
                        "Open",
                        "password.txt",
                        Some((&["*.moa"], "MOA Files")),
                    ) {
                        Some(file) => open_file = file,
                        None => open_file = "null".to_string(),
                    }

                    if open_file != "null".to_string() {
                        HAS_LOADED_MOA.store(true, Ordering::Relaxed);

                        let mut moa_path = LOADED_MOA_PATH.lock().unwrap();
                        *moa_path = open_file.clone();

                        let data = fs::read_to_string(open_file).expect("Unable to read file");

                        let mut json = LOADED_JSON.lock().unwrap();

                        *json = serde_json::from_str(&data)
                            .expect("JSON does not have correct format.");

                        self.name = json["pdata"]["name"].as_str().unwrap().to_string();
                        self.description = json["pdata"]["desc"].as_str().unwrap().to_string();

                        let json_race = json["key"]["race"].as_i64().unwrap();

                        let sex_and_race = get_sex_and_race(json_race);

                        self.sex = sex_and_race.0;
                        self.race = sex_and_race.1;
                    }
                }

                if ui.button("Quit").clicked() {
                    std::process::exit(0);
                }
            });

            if SHOULD_RESET_UI.load(Ordering::Relaxed) {
                *self = MyApp::default();
                SHOULD_RESET_UI.store(false, Ordering::Relaxed)
            }
        });
    }
}

fn get_sex_and_race(json_race: i64) -> (Sex, Race) {
    // Don't support the other races yet.
    match json_race {
        2 => return (Sex::Male, Race::Mercenary),
        3 => return (Sex::Male, Race::Templar),
        4 => return (Sex::Male, Race::Harakim),
        _ => panic!("Invalid json_race"),
    };
}
