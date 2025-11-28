#filetracker-2025

THE FILE SYSTEM MANAGER EXPECTS INPUTS LIKE OF THE FORM

RUN BUILD.BAT, a myprogram.exe file gets created. RUN 

<FUNCTION> <FILENAME> [text] - depending on the function.
To exit, simply type EXIT.

1. CREATE- Simply creates a file with the given name. 
	MUST NOT CONTAIN SPACES, OTHERWISE ONLY THE FIRST WORD WILL BE COUNTED.

2. READ- Reads the contents of the active version of the file. Prints out a string (the message).

3. INSERT - Appends the given text to the given file's contents. If the active version is a Snapshot, creates a new version and adds the text to it.

4. UPDATE - Replaces active version's text and follows same versioning logic as INSERT.

5. SNAPSHOT - Snapshots the current active version of the given file with a message.
	IF THERE IS NO MESSAGE GIVEN FOR THE SNAPSHOT, IT WILL NOT CONSIDER TO BE SNAPSHOT-ED AND WILL CONSIDER IT AS RUNNING AN ACTIVE VERSION.

6. ROLLBACK - Enter the version number (files are versioned +1 after every snapshot). If found, will rollback to the given version.

7. HISTORY - couldn't implement on time



BIGGEST_FILES, SYSTEM_FILES - Implemented it using custom heaps, but due to some unknown segmentation error it wouldn't work. Even after multiple attempts at debugging.
Original code exists in cpp file but now it is useless since I bypass that code whenever these functions are called to avoid crashing down of the whole system.

Made by Atharva Deshmukh, 2024EE30692.
