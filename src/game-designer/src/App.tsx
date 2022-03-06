import React, { useState } from 'react';
import './App.css';
import Button from '@mui/material/Button';
import { TextField } from '@mui/material';

function App() {
  const [idToSearch, setIdToSearch] = useState('');
  
  const onClickHandler = async () => {
    const response = await fetch('http://localhost:5556/api/v1/characters/' + idToSearch);
    const myJson = await response.json(); //extract JSON from the http response
    
    console.log(myJson);
  }

  return (
    <div className="App">
      <header className="App-header">
        <h1>Men Among Gods - Game Designer</h1>
      </header>
      <TextField onChange={(event)=>{ setIdToSearch(event.target.value) }} id="standard-basic" label="Enter Id" variant="standard" />
      <Button onClick={onClickHandler} variant="contained">Search</Button>
    </div>
  );
}

export default App;
