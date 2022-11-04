# Changelog

All notable changes to decision table editor will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### [TO-DO]

- Creating swap file.
- Handling existing swap files before opening original file (somehow similar to vi).
- Deleting all whitespaces before next vertical line.
- Deleting all but one whitespace before next vertical line.
- Deleting empty bottom lines in all cells in a row.
- Display help when F1 pressed.
- Switch to editing from help when ESC pressed.
- Display funny info when the size of the terminal is too small.
- Repaint only required regions.
- Repaint while terminal window is resized.
- Handle mouse clicks.
- Disable editing rule numbers - adjust rule numbers automatically.
- Disable free editing of the hit policy - accept only allowed characters.
- Insert decision rule.
- Delete decision rule.
- Reposition decision rule (up<->down (horizontal), left<->right (vertical)).
- Add input clause.
- Delete input clause.
- Reposition input clause.
- Add output clause.
- Delete output clause.
- Reposition output clause.
- Add annotation clause.
- Remove annotation clause.
- Reposition annotation clause.
- Join cells.
- Split cells.
- Undo/Redo.
- Delete multirow.
- Replace mode.
- Insert after mode.
- Jump to row above/below when moving horizontally.
- Add command line option to save example decision tables.
- Add initializer screen with selecting options for new decision tables.
- Interactive decision table initializer.
- Recognize decision table on input.
- Parse and compile decision table.
- Evaluate decision table with test data.

## [Unreleased]

- Saving changes to file.

## [0.0.2] - 2022-11-03

### Added

- Inserting a new line in a cell when pressing ENTER.
- Deletion continuation to previous row with deleting last empty line in cell.
- Reserve status bar at the bottom line.

## [0.0.1] - 2022-10-22

### Added

- Opening and displaying a decision table.
- Simple cursor moving operations.
- Simple editing operations.
- Opening a file containing a decision table.
- Handling command-line arguments. Type `atto --help` for details.
- Move around the decision table using arrows, TAB, END and HOME keys.
- Insert text into cell.
- Delete text under cursor.
- Delete text before cursor.
- Scrolling view when the content is larger than width and/or height of the terminal.
- When information item name is present it is edit separately from the decision table body.
- Hiding cursor during repainting.