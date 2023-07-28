import { useState } from "react";
import { invoke } from "@tauri-apps/api/tauri";
import "./App.css";
import CharacterDetails from "./CharacterDetails";

function App() {
  const [greetMsg, setGreetMsg] = useState("");
  const [name, setName] = useState("");

  async function greet() {
    // Learn more about Tauri commands at https://tauri.app/v1/guides/features/command
    setGreetMsg(await invoke("greet", { name }));
  }

  return <>
    <div className="container">
      <h1>Men Among Gods</h1>
      <div className="column">
        <CharacterDetails />
      </div>
    </div>
  </>
}

export default App;
