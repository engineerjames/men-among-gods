import { DataGrid, GridColDef } from '@mui/x-data-grid';
import React from 'react'

export interface CharacterAttribute {
    data: Array<number>;
    name: string;
}

export interface CharacterAttributesProps {
    attributes?: Array<CharacterAttribute>;
}

const columns: GridColDef[] = [
    {
        field: 'id',
        headerName: 'Name',
        headerAlign: 'center',
        width: 100,
        align: 'left',
        sortable: false,
        editable: false
    },
    {
        field: 'baseValue',
        headerName: 'Base',
        headerAlign: 'center',
        description: 'Base value of the attribute.',
        width: 100,
        align: 'center',
        sortable: false,
        editable: true,
    },
    {
        field: 'presetModifier',
        headerName: 'Preset',
        headerAlign: 'center',
        description: 'Preset modifier; race/npc dependent.',
        width: 100,
        align: 'center',
        sortable: false,
        editable: true,
    },
    {
        field: 'maxValue',
        headerName: 'Max',
        headerAlign: 'center',
        description: 'Race specific maximum.',
        type: 'number',
        align: 'center',
        width: 100,
        sortable: false,
        editable: true,
    },
    {
        field: 'difficultyToRaise',
        headerName: 'Difficulty',
        headerAlign: 'center',
        description: 'Race specific difficulty to raise.',
        align: 'center',
        sortable: false,
        width: 100,
    },
    {
        field: 'dynamicModifier',
        headerName: 'Modifier',
        headerAlign: 'center',
        description: 'Dynamic modifier based on equipment and/or spells.',
        align: 'center',
        sortable: false,
        width: 100,
    },
    {
        field: 'total',
        headerName: 'Total',
        headerAlign: 'center',
        description: 'Total modified value--typically not stored in templates.',
        align: 'center',
        sortable: false,
        width: 100,
    },
];

// character stats
// [0]=bare value, 0=unknown
// [1]=preset modifier, is race/npc dependend
// [2]=race specific maximum
// [3]=race specific difficulty to raise (0=not raisable, 1=easy ... 10=hard)
// [4]=dynamic modifier, depends on equipment and spells
// [5]=total value

function CharacterAttributes(props: CharacterAttributesProps) {

    const rows: any = [];
    props?.attributes?.map((attr) => {
        console.log(attr);
        rows.push({
            id: attr.name,
            baseValue: attr.data[0],
            presetModifier: attr.data[1],
            maxValue: attr.data[2],
            difficultyToRaise: attr.data[3],
            dynamicModifier: attr.data[4],
            total: attr.data[5]
        })
    });

    return (
        <div style={{ height: 400, width: '100%' }}>
            <DataGrid
                rows={rows}
                columns={columns}
                pageSize={5}
                rowsPerPageOptions={[5]}
                disableSelectionOnClick
            />
        </div>
    );
}

export default CharacterAttributes