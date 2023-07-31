import { Dispatch, FunctionComponent, SetStateAction } from "react";
import { Stack } from "@mui/material";

interface PropType {
    ip: string,
    port: string,
    onChangeIp: Dispatch<SetStateAction<string>>,
    onChangePort: Dispatch<SetStateAction<string>>,
}

const ServerDetails: FunctionComponent<PropType> = (props) => {
    return <>
        <h4>Server Details</h4>
        <Stack spacing={2}>
            <input
                value={props.ip}
                onChange={(e) => { props.onChangeIp(e.target.value) }}
                required id="outlined-basic"
                placeholder="Description"
                type="text" />
            <input
                value={props.port}
                onChange={(e) => { props.onChangePort(e.target.value) }}
                required id="outlined-basic"
                placeholder="Description"
                type="text" />
        </Stack>
    </>
}

export default ServerDetails;