# AnalyzeGPX_Qt
Analyse Garmin GPX files (Qt version)

Shows routes, tracks and waypoints of a GPX file. Tested only with Garmin GPX files.

On the left side ("GPX files list") there is a master view of a splitview, which lists the Garmin devices with their corresponding GPX files for a folder "/Garmin/GPX"

On the right side ("GPX Content"), the content (routes, tracks, waypoints) of a GPX file is shown

The "Open GPX file" button lets you locate and open a specific GPX file in the file system and shows it in the "GPX Content".
The "Load Garmin devices" looks for attached devices/volumes for a folder "/Garmin/GPX" and lists all gpx files found in "GPX files list".
Clicking on a GPX file in the "GPX files list" will show the content of the GPX file in the "GPX Content" view.

Known: issues:
- Does not work with dark mode (MacOS)
