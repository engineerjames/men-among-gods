import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld('electron', {
    openDialog: (method: any, config: any) => ipcRenderer.invoke('dialog', method, config),
    readFile: (method: any, config : any) => ipcRenderer.invoke('readSelectedFile', method, config),
    }
});