# Attr [![Flattr this][flatter_png]][flatter]

Display and set attributes on files and directories.

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

````batch
C:\>rem turn off archive bit on files in c:\
C:\>attr -a-

C:\>rem turn off archive bit on files on drive c:
C:\>attr -a- -R

C:\>rem display what files have their archive bit set on drive c: (but don't change the bit):
C:\>attr -a- -R --dry-run *.*

C:\>rem display what files don't have their archive bit set on drive c: (but don't change the bit):
C:\>attr -a+ -R --dry-run *.*
````

## Verify a Release

To verify a release, download the .zip, .sha256, and .asc files for the release 
(replacing attr-1.6-win32.zip with the release you are verifying):

````
$ wget https://github.com/rasa/attr/releases/download/v1.6/attr-1.6-win32.zip
$ wget https://github.com/rasa/attr/releases/download/v1.6/attr-1.6-win32.zip.sha256
$ wget https://github.com/rasa/attr/releases/download/v1.6/attr-1.6-win32.zip.asc
````

Next, check that sha256sum reports "OK":
````
$ sha256sum -c attr-1.6-win32.zip.sha256
attr-1.6-win32.zip: OK
````

Lastly, check that GPG reports "Good signature":

````
$ gpg --keyserver hkps.pool.sks-keyservers.net --recv-key 0x105a5225b6ab4b22
$ gpg --verify attr-1.5-win32.zip.asc attr-1.5-win32.zip
gpg:                using RSA key 0xFF914F74B4BB6EF3
gpg: Good signature from "Ross Smith II <ross@smithii.com>" [ultimate]
...
````

## Contributing

To contribute to this project, please see [CONTRIBUTING.md](CONTRIBUTING.md).

## Bugs

To view existing bugs, or report a new bug, please see [issues](../../issues).

## Changelog

To view the version history for this project, please see [CHANGELOG.md](CHANGELOG.md).

## License

This project is [MIT licensed](LICENSE).

## Contact

This project was created and is maintained by [Ross Smith II][] [![endorse][endorse_png]][endorse]

Feedback, suggestions, and enhancements are welcome.

[Ross Smith II]: mailto:ross@smithii.com "ross@smithii.com"
[flatter]: https://flattr.com/submit/auto?user_id=rasa&url=https%3A%2F%2Fgithub.com%2Frasa%2Fattr
[flatter_png]: http://button.flattr.com/flattr-badge-large.png "Flattr this"
[endorse]: https://coderwall.com/rasa
[endorse_png]: https://api.coderwall.com/rasa/endorsecount.png "endorse"

