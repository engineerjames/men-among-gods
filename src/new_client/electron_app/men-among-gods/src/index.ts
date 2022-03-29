import { spawn } from 'child_process';
import { app, BrowserWindow, dialog, ipcMain } from 'electron';
import { cwd } from 'process';

var path = require('path');
var fs = require('fs/promises');
var fs2 = require('fs');

// This allows TypeScript to pick up the magic constant that's auto-generated by Forge's Webpack
// plugin that tells the Electron app where to look for the Webpack-bundled app code (depending on
// whether you're running in development or production).
declare const MAIN_WINDOW_WEBPACK_ENTRY: string;
declare const MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY: string;

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  // eslint-disable-line global-require
  app.quit();
}

const createWindow = (): void => {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    height: 850,
    width: 610,
    autoHideMenuBar: true,
    center: true,
    titleBarOverlay: true,
    frame: true,
    webPreferences: {
      nodeIntegration: false, // is default value after Electron v5
      contextIsolation: true, // protect against prototype pollution
      preload: MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY // use a preload script
    }
  });

  // and load the index.html of the app.
  mainWindow.loadURL(MAIN_WINDOW_WEBPACK_ENTRY);

  // Open the DevTools.
  // mainWindow.webContents.openDevTools();
};

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.on('ready', createWindow);

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and import them here.
app.whenReady().then(() => {
  ipcMain.handle('dialog', (event: Event, method: any, params: any) => {
    return dialog.showOpenDialog({ properties: ['openFile'] });
  });
});

app.whenReady().then(() => {
  ipcMain.handle('readSelectedFile', (event: Event, method: any, params: any) => {
    return fs.readFile(method, 'utf-8');
  });
});

app.whenReady().then(() => {
  ipcMain.handle('game', (event: Event, filepath: any, params: any) => {

    let out = fs2.openSync('./out.log', 'a');
    let err = fs2.openSync('./out.log', 'a');

    let fullyqualifiedpath = path.join(process.cwd(), 'client', 'MenAmongGods.exe');
    console.log('Loading MenAmongGods EXE from ' + fullyqualifiedpath);
    const child = spawn(fullyqualifiedpath, params, {
      detached: true,
      cwd: path.join(process.cwd(), 'client'),
      stdio: ['ignore', out, err],
    });

    // TODO: Enable later?
    // child.unref();
    // app.quit();
  });
});