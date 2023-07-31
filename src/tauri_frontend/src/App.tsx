import { Backdrop, CircularProgress, Divider, Stack } from "@mui/material";
import "./App.css";
import CharacterDetails from "./CharacterDetails";
import ServerDetails from "./ServerDetails";
import { useState } from "react";
import { invoke } from "@tauri-apps/api";

function App() {

  // Server Details
  const [ip, setIp] = useState("127.0.0.1");
  const [port, setPort] = useState("5555");

  // Player Details
  const [name, setName] = useState("");
  const [pass, setPass] = useState("");
  const [desc, setDesc] = useState("");
  const [sex, setSex] = useState('male');
  const [characterClass, setCharacterClass] = useState('templar');

  // UI-Specific
  const [buttonsAreEnabled, setbuttonsAreEnabled] = useState(true);

  async function play() {
    let sexAsInt = sex === "male" ? 1 : 2;

    let characterClassAsInt = 1;
    switch (characterClass) {
      case "templar":
        characterClassAsInt = 1;
        break;
      case "harakim":
        characterClassAsInt = 2;
        break;
      case "mercenary":
        characterClassAsInt = 3;
        break;
      default:
        break;
    }

    await invoke("set_server_data", {
      ipAddress: ip,
      port: port,
    });

    await invoke("set_player_data", {
      name: name,
      pass: pass,
      desc: desc,
      sex: sexAsInt,
      race: characterClassAsInt
    });

    await invoke("play", {});
  }

  let clearValues = () => {
    setName("");
    setPass("");
    setDesc("");
    setSex('male');
  }

  return <>
    <div className="container">
      <h1>Men Among Gods</h1>
      <div className="column">
        <Stack spacing={2} visibility={() => {
          return (buttonsAreEnabled ? "visible" : "hidden");
        }}>
          <CharacterDetails name={name} pass={pass} desc={desc} sex={sex} characterClass={characterClass}
            onChangeName={setName} onChangePass={setPass} onChangeDesc={setDesc} onChangeSex={setSex} onChangeCharacterClass={setCharacterClass} />
          <ServerDetails ip={ip} onChangeIp={setIp} port={port} onChangePort={setPort} />
          <Stack spacing={2} direction="row" divider={<Divider orientation="vertical" flexItem />} >
            <button onClick={() => {
              setbuttonsAreEnabled(false);
              play();
            }}>Play</button>
            <button onClick={() => {
              clearValues()
            }}>New</button>
          </Stack>
        </Stack >
        <Backdrop
          sx={{ color: '#fff', zIndex: (theme) => theme.zIndex.drawer + 1 }}
          open={!buttonsAreEnabled}
        >
          <CircularProgress color="inherit" />
        </Backdrop>

      </div>
    </div>
  </>
}

export default App;
