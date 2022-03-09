import { Paper, Table, TableBody, TableCell, TableContainer, TableHead, TableRow } from '@mui/material';
import React from 'react'

export interface CharacterAttribute {
    data: Array<number>;
    name: string;
}

export interface CharacterAttributesProps {
    attributes?: Array<CharacterAttribute>;
}

// character stats
// [0]=bare value, 0=unknown
// [1]=preset modifier, is race/npc dependend
// [2]=race specific maximum
// [3]=race specific difficulty to raise (0=not raisable, 1=easy ... 10=hard)
// [4]=dynamic modifier, depends on equipment and spells
// [5]=total value
function CharacterAttributes(props: CharacterAttributesProps) {
    return (
        <>
        <h3>Character Attributes</h3>
        <TableContainer component={Paper}>
            <Table sx={{ minWidth: 650 }} aria-label="simple table">
                <TableHead>
                    <TableRow>
                        <TableCell>Attribute Name</TableCell>
                        <TableCell align="right">Base Value</TableCell>
                        <TableCell align="right">Preset Modifier</TableCell>
                        <TableCell align="right">Maximum Value</TableCell>
                        <TableCell align="right">Difficulty to Raise [0-10]</TableCell>
                        <TableCell align="right">Dynamic Modifier (equip + spells)</TableCell>
                        <TableCell align="right">Total</TableCell>
                    </TableRow>
                </TableHead>
                <TableBody>
                    {props?.attributes?.map((attr) => (
                        <TableRow
                            key={attr.name}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                        >
                            <TableCell component="th" scope="row">
                                {attr.name}
                            </TableCell>
                            <TableCell align="right">{attr.data[0]}</TableCell>
                            <TableCell align="right">{attr.data[1]}</TableCell>
                            <TableCell align="right">{attr.data[2]}</TableCell>
                            <TableCell align="right">{attr.data[3]}</TableCell>
                            <TableCell align="right">{attr.data[4]}</TableCell>
                            <TableCell align="right">{attr.data[5]}</TableCell>

                        </TableRow>
                    ))}
                </TableBody>
            </Table>
        </TableContainer>
        </>
    )
}

export default CharacterAttributes