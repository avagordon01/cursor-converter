# Windows to Linux cursor converter

![dinosaur](screenshots/dinosau21.png)
![dinosaur](screenshots/dinosau22.png)
![dinosaur](screenshots/dinosau23.png)
![dinosaur](screenshots/dinosau24.png)
![dinosaur](screenshots/dinosau25.png)
![dinosaur](screenshots/dinosau26.png)
![dinosaur](screenshots/dinosaur1.png)
![dinosaur](screenshots/dinosaur2.png)
![dinosaur](screenshots/dinosaur3.png)
![dinosaur](screenshots/dinosaur4.png)
![dinosaur](screenshots/dinosaur5.png)
![dinosaur](screenshots/dinosaur6.png)

## Depends

- ImageMagick
- Windows Cursors, either `.ani` or `.cur`. (A default dinosaur theme is included)

## Build Ani2Ico

```
cd ani2ico
make
```

## Conversion

Input files should be in `inputs/*.ani` and `inputs/*.cur`
Output files will go to `outputs/CURSORNAME/CURSORNAME*`

```
./convert.sh
```

## Usage

Start with a default cursor theme, something like Adwaita

```
mkdir -p ~/.icons/THEMENAME
cp /usr/share/icons/Adwaita/cursors ~/.icons/THEMENAME
```

Replace the cursors you want

```
cp outputs/CURSORNAME/CURSORNAME ~/.icons/THEMENAME/cursors/CURSOR_TO_REPLACE
```

You may also have to select the cursor theme.
In Gnome, this is done using `gnome-tweak-tool`, in `Appearance/Themes/Cursor` select `THEMENAME`.
