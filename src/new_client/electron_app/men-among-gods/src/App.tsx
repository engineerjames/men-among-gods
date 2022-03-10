import React, { useState } from 'react';
import './App.css';
import SexSelection, { Sex } from './SexSelection';
import RaceSelection, { Race } from './RaceSelection';
import CharacterInput from './CharacterInput';
import { Box, Button, ButtonGroup, Divider } from '@mui/material';

function App() {

  const [sex, setSex] = useState(Sex.Female);
  const [race, setRace] = useState(Race.Templar);

  return (
    <div className="App">
      <header className="App-header">
        Men Among Gods
      </header>
      <Box component="form"
        alignContent='left'
        sx={{
          '& .MuiTextField-root': { m: 1, width: '25ch' },
        }}
        noValidate
        autoComplete="off">

        <CharacterInput />

        <SexSelection selectedSex={sex} />
        <Divider orientation="vertical" flexItem />
        <RaceSelection selectedRace={race} />
        <Divider orientation="vertical" flexItem />
        <Button sx={{ m: 2 }} size='large' variant="contained">New</Button>
        <Button sx={{ m: 2 }} size='large' variant="contained">Load</Button>
        <Button sx={{ m: 2 }} size='large' variant="contained">Save</Button>
      </Box>
    </div>
  );
}

export default App;
