import React, { useEffect, useState } from 'react';
import './App.css';
import SexSelection, { Sex } from './SexSelection';
import RaceSelection, { Race } from './RaceSelection';
import CharacterInput from './CharacterInput';
import { Box, Button, Divider } from '@mui/material';

// This is essentially duplicated logic from ClientTypes.h
const intToRaceAndSex = (kindred: number): [Race, Sex] => {
  switch ( kindred )
  {
  case 3:
    return [Race.Templar, Sex.Male];
  case 2:
    return [Race.Mercenary, Sex.Male ];
  case 4:
    return [Race.Harakim, Sex.Male ];
  case 13:
    return [Race.Seyan, Sex.Male ];
  case 543:
    return [Race.God, Sex.Male ];
  case 544:
    return [Race.ArchTemplar, Sex.Male ];
  case 545:
    return [Race.ArchHarakim, Sex.Male ];
  case 546:
    return [Race.Sorceror, Sex.Male ];
  case 547:
    return [Race.Warrior, Sex.Male ];
  case 77:
    return [Race.Templar, Sex.Female ];
  case 76:
    return [Race.Mercenary, Sex.Female ];
  case 78:
    return [Race.Harakim, Sex.Female ];
  case 79:
    return [Race.Seyan, Sex.Female ];
  case 548:
    return [Race.God, Sex.Female];
  case 549:
    return [Race.ArchTemplar, Sex.Female ];
  case 550:
    return [Race.ArchHarakim, Sex.Female ];
  case 551:
    return [Race.Sorceror, Sex.Female ];
  case 552:
    return [Race.Warrior, Sex.Female ];
  default:
    return [Race.Templar, Sex.Male ];
  }
}

interface xbutton {
  name: string;
  skill_id: number;
}

interface key {
  name: string;
  pass1: number;
  pass2: number;
  race: number;
  usnr: number;
}

interface MOAFile {
  pdata: {
    name: string;
    desc: string;
    ref: string;
    show_names: number;
    show_percent_health: number;
    xbutton: Array<xbutton>;
  };
  key: key;
}

function App() {

  const [sex, setSex] = useState(Sex.None);
  const [race, setRace] = useState(Race.None);
  const [name, setName] = useState('');
  const [desc, setDesc] = useState('');
  const [pass, setPass] = useState('');
  const [moaFile, setMoaFile] = useState<MOAFile>();

  const clearState = () => {
    setSex(Sex.None);
    setRace(Race.None);
    setName('');
    setDesc('');
    setPass('');
  }

  useEffect(() => {
    if (moaFile) {
      console.log('Setting name to' + moaFile.pdata.name);
      setName(moaFile.key.name);
      setDesc(moaFile.pdata.desc);

      // Now set the sex and race
      let [race, sex] = intToRaceAndSex(moaFile.key.race);
      setSex(sex);
      setRace(race);
    }
    else {
      console.log('Invalid MOA file: ' + moaFile);
    }
  }, [moaFile])


  const onClickHandler = () => {
    const dialogConfig = {
      title: 'Select a file',
      buttonLabel: 'This one will do',
      properties: ['openFile']
    };

    // @ts-ignore: TS isn't aware of context 
    window.electron.openDialog('showOpenDialog', dialogConfig)
      // @ts-ignore: TS isn't aware of context 
      .then((result) => {
        // @ts-ignore: TS isn't aware of context 
        window.electron.readFile(result.filePaths[0]).then((result2) => {
          let moaFileLoaded: MOAFile = JSON.parse(result2) as MOAFile;
          console.log(moaFileLoaded);
          setMoaFile(moaFileLoaded);
        })
      });

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
        <Button sx={{ m: 2 }} size='large' variant="contained" onClick={() => { onClickHandler(); }}>Load</Button>
        <Button sx={{ m: 2 }} size='large' variant="contained">Save</Button>
        <Button sx={{ m: 6 }} size='large' variant="contained">Submit</Button>
      </Box>
    </div>
  );
}

export default App;
