[Setup]
AppName=Calendrier
AppVersion=1.0
DefaultDirName={pf}\Calendrier
DefaultGroupName=Calendrier

[Files]
Source: "Calendrier.exe"; DestDir: "{pf}\Calendrier"
Source: "events.exe"; DestDir: "{pf}\Calendrier"
Source: "saints.exe"; DestDir: "{pf}\Calendrier"
Source: "bdd"; DestDir: "{pf}\Calendrier"
Source: "croix.png"; DestDir: "{pf}\Calendrier"
Source: "dq.png"; DestDir: "{pf}\Calendrier"
Source: "nl.png"; DestDir: "{pf}\Calendrier"
Source: "pl.png"; DestDir: "{pf}\Calendrier"
Source: "pq.png"; DestDir: "{pf}\Calendrier"
Source: "clock_B.png"; DestDir: "{pf}\Calendrier"
Source: "s_hand.png"; DestDir: "{pf}\Calendrier"
Source: "m_hand.png"; DestDir: "{pf}\Calendrier"
Source: "h_hand.png"; DestDir: "{pf}\Calendrier"
Source: "fond.png"; DestDir: "{pf}\Calendrier"
Source: "icon.ico"; DestDir: "{pf}\Calendrier"
Source: "QtGuid4.dll"; DestDir: "{pf}\Calendrier"
Source: "QtCored4.dll"; DestDir: "{pf}\Calendrier"
Source: "QtSqld4.dll"; DestDir: "{pf}\Calendrier"
Source: "libgcc_s_dw2-1.dll"; DestDir: "{pf}\Calendrier"
Source: "mingwm10.dll"; DestDir: "{pf}\Calendrier"
Source: "sqldrivers\qsqlited4.dll"; DestDir: "{pf}\Calendrier\sqldrivers"

[Icons]
Name: "{group}\Calendrier"; Filename: "{pf}\Calendrier\Calendrier.exe"; IconFilename: "{pf}\Calendrier\icon.ico"
Name: "{userdesktop}\Calendrier"; Filename: "{pf}\Calendrier\Calendrier.exe"; IconFilename: "{pf}\Calendrier\icon.ico"
Name: "{group}\Uninstall"; Filename: "{pf}\Calendrier\{uninstallexe}"
