# Attr

Display and set attributes on files and directories

## Usage

Usage: attr [options] filespec [filespec]

Options:
````
-a | --archive     + | -  Set/reset archive bit
-r | --readonly    + | -  Set/reset read only bit
-h | --hidden      + | -  Set/reset hidden bit
-s | --system      + | -  Set/reset system bit
-n | --not-indexed + | -  Set/reset content not indexed bit
-o | --offline     + | -  Set/reset offline bit
-t | --temporary   + | -  Set/reset temporary bit
-d | --directories        Set/reset bits on directories
-y | --dry-run            Change nothing, just report what would change
-i | --hide-attributes    Do not show attributes
-e | --abort-on-error     Abort if an error occurs
-R | --recursive          Scan directories recursively
-q | --quiet              Display less information
-v | --verbose            Display more information
-V | --version            Show version and copyright information and quit
-? | --help               Show this help message and quit
````

Works on hidden and system files.
Doesn't abort on error (unless you use the -e option).

When displaying attributes, the following characters are used:

````
Character Meaning
--------- -------
-         The attribute is not set, and will not be changed
_         The attribute was set, and will be reset (turned off)
a         Archive     attribute is set, and will not be changed
r         Read-only   attribute is set, and will not be changed
h         Hidden      attribute is set, and will not be changed
s         System      attribute is set, and will not be changed
n         Not-indexed attribute is set, and will not be changed
o         Offline     attribute is set, and will not be changed
t         Temporary   attribute is set, and will not be changed
A         Archive     attribute is not set, and will be set
R         Read-only   attribute is not set, and will be set
H         Hidden      attribute is not set, and will be set
S         System      attribute is not set, and will be set
N         Not-indexed attribute is not set, and will be set
O         Offline     attribute is not set, and will be set
T         Temporary   attribute is not set, and will be set
````

## Examples

````
C:\>rem turn off archive bit on files in c:\
C:\>attr -a- 

C:\>rem turn off archive bit on files on drive c:
C:\>attr -a- -R

C:\>rem display what files have their archive bit set on drive c: (but don't change the bit):
C:\>attr -a- -R --dry-run *.*

C:\>rem display what files don't have their archive bit set on drive c: (but don't change the bit):
C:\>attr -a+ -R --dry-run *.*
````

## Contributing

To contribute to this project, please see [CONTRIBUTING.md](CONTRIBUTING.md).

## Bugs

To view existing bugs, or report a new bug, please see the [issues](/issues) page for this project.

## License

This project is [MIT licensed](LICENSE).

## Changelog

Please see [CHANGELOG.md](CHANGELOG.md) for the version history for this project.

## Contact

This project was originally developed by [Ross Smith II](mailto:ross@smithii.com).
Any enhancements and suggestions are welcome.
