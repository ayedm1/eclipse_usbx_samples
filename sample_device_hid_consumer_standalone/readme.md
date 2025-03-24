🔆 Light Control Commands

// Increase Brightness
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x0060);  // Brightness Up

// Decrease Brightness
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x0061);  // Brightness Down

// Turn Light On/Off
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x0062);  // Power Toggle

// Dim Light
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x0063);  // Dim

// Max Brightness
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x0064);  // Bright

🎵 Media Control Commands

// Volume Up
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x00E9);  // Volume Up

// Volume Down
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x00EA);  // Volume Down

// Mute
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x00E2);  // Mute

// Play/Pause
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x00CD);  // Play/Pause

// Next Track
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x00B5);  // Next Track

// Previous Track
Send_Consumer_Control_Report(&hUsbDeviceFS, 0x00B6);  // Previous Track