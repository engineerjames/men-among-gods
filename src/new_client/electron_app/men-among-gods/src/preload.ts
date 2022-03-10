import { contextBridge, ipcRenderer } from "electron";

console.log('PRELOADED');

contextBridge.exposeInMainWorld('electron', {
    openDialog: (method: any, config: any) => ipcRenderer.invoke('dialog', method, config)
});