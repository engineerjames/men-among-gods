#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")] // hide console window on Windows in release

use eframe::egui;
use std::sync::atomic::{AtomicBool, Ordering};
use std::thread::{self};
use tinyfiledialogs::{MessageBoxIcon, YesNo};

static SHOULD_RESET_UI: AtomicBool = AtomicBool::new(false);

fn main() -> Result<(), eframe::Error> {
    env_logger::init(); // Log to stderr (if you run with `RUST_LOG=debug`).
    let options = eframe::NativeOptions {
        initial_window_size: Some(egui::vec2(400.0, 600.0)),
        ..Default::default()
    };
    eframe::run_native(
        "Men Among Gods", // TODO: Include version information
        options,
        Box::new(|_cc| Box::<MyApp>::default()),
    )
}

#[derive(PartialEq)]
enum Sex {
    Male,
    Female,
}

#[derive(PartialEq)]
enum Race {
    Templar,
    Mercenary,
    Harakim,
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
        "hello",
        "yes or no?",
        MessageBoxIcon::Question,
        YesNo::No,
    );

    return choice;
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
                if ui.button("Play").clicked() {}
                if ui.button("New").clicked() {
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
                    match tinyfiledialogs::open_file_dialog("Open", "password.txt", None) {
                        Some(file) => open_file = file,
                        None => open_file = "null".to_string(),
                    }

                    println!("{}", open_file);
                    // TODO: Add loading from json file
                }
                if ui.button("Save").clicked() {
                    let save_file: String;
                    match tinyfiledialogs::save_file_dialog("Save", "password.txt") {
                        Some(file) => save_file = file,
                        None => save_file = "null".to_string(),
                    }
                    println!("{}", save_file);

                    // TODO: Add saving to json file
                }
            });

            if SHOULD_RESET_UI.load(Ordering::Relaxed) {
                *self = MyApp::default();
                SHOULD_RESET_UI.store(false, Ordering::Relaxed)
            }
        });
    }
}
