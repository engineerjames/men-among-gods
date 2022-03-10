import React, { useState } from 'react';
import './App.css';
import SexSelection, { Sex } from './SexSelection';
import RaceSelection, { Race } from './RaceSelection';
import CharacterInput from './CharacterInput';
import { Box, Button, Divider } from '@mui/material';
import { ipcRenderer } from 'electron';

function App() {

  ipcRenderer.send('openFile', () => { 
     console.log("Event sent."); 
  }); 
  
  ipcRenderer.on('fileData', (event : any, data : any) => { 
    console.log(data);
  });


  const [sex, setSex] = useState(Sex.None);
  const [race, setRace] = useState(Race.None);
  const [name, setName] = useState('');
  const [desc, setDesc] = useState('');
  const [pass, setPass] = useState('');

  const clearState = () => {
    setSex(Sex.None);
    setRace(Race.None);
    setName('');
    setDesc('');
    setPass('');
  }


  return (
    <div className="App">
      <header className="App-header">
        Men Among Gods
      </header>
      <Box component="form"
        alignContent='left'
        sx={{
          '& .MuiTextField-root': { m: 2, width: '25ch' },
        }}
        noValidate
        autoComplete="off">

        <CharacterInput name={name} description={desc} password={pass}
          setName={setName} setDesc={setDesc} setPass={setPass} />

        <SexSelection selectedSex={sex} setSex={setSex} />
        <Divider orientation="vertical" flexItem />
        <RaceSelection selectedRace={race} setRace={setRace} />
        <Divider orientation="vertical" flexItem />
        <Button sx={{ m: 2 }} onClick={() => { clearState(); }} size='large' variant="contained">New</Button>
        <Button sx={{ m: 2 }} size='large' variant="contained">Load</Button>
        <Button sx={{ m: 2 }} size='large' variant="contained">Save</Button>
        <Button sx={{ m: 6 }} size='large' variant="contained">Submit</Button>
      </Box>
    </div>
  );
}

export default App;
