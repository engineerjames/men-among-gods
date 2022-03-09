import { Grid, List, ListItem, ListItemText, Stack, Typography } from '@mui/material';
import React from 'react'

export interface TextDisplayProps {
    text?: Array<string>;
}

function TextDisplay(props: TextDisplayProps) {
    return (
        <>
            <h3>Text Display</h3>
            <Grid container spacing={2}>
                <Grid item xs={12} md={6}>
                    <List dense={false}>
                        {props.text?.map((text, index) => {
                            return (
                                <ListItem key={index}>
                                    <ListItemText key={index} primary={text} />
                                </ListItem>
                            )
                        })}
                    </List>
                </Grid>
            </Grid>
        </>
    )
}

export default TextDisplay