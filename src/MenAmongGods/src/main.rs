#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")] // hide console window on Windows in release

use eframe::egui;

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

struct MyApp {
    name: String,
    description: String,
    sex: Sex,
    race: String,
    password: String,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            name: "".to_owned(),
            description: "".to_owned(),
            sex: Sex::Male,
            race: "".to_owned(),
            password: "".to_owned(),
        }
    }
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

            ui.horizontal(|ui| {
                ui.radio_value(&mut self.sex, Sex::Male, "Male");
                ui.radio_value(&mut self.sex, Sex::Female, "Female");
            });

            //ui.add(egui::Slider::new(&mut self.sex, 0..=120).text("age"));

            ui.horizontal(|ui| {
                if ui.button("Play").clicked() {}
                if ui.button("New").clicked() {}
                if ui.button("Load").clicked() {}
                if ui.button("Save").clicked() {}
            });
        });
    }
}
