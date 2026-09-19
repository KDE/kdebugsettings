# KDebugSettings

Configure the debug output of Qt and KDE applications, without
recompiling them and without editing `qtlogging.ini` by hand.

Qt applications send their diagnostic messages through *logging
categories*: named channels such as `org.kde.pim.kmail` or
`kf.kio.core`, each of which can be enabled per severity (debug, info,
warning, critical). Most of them are silent by default. KDebugSettings
lists every category installed on the system, lets you choose how
verbose each one should be, and writes the result to the file Qt reads
at startup:

```text
$XDG_CONFIG_HOME/QtProject/qtlogging.ini   (usually ~/.config/...)
```

Rules apply to applications started *after* they are saved; running
applications are not affected.

## Quick start

Turn on everything for one application, from the GUI:

1. Start `kdebugsettings`.
2. Type part of the application name in the search field, for example
   `kmail`. The filter matches the description, the category name and
   the C++ identifier, so `KMAIL_LOG` works too.
3. Select the rows you care about, then press **Enable All Debug**, or
   pick a level in the drop down box of a single row.
4. Press **OK**, restart the application and watch the journal:

```bash
journalctl -f -t kmail
```

The same thing from the command line, without opening the dialog:

```bash
kdebugsettings --debug-mode Full org.kde.pim.kmail org.kde.pim.messagelist
kdebugsettings --enable-full-debug    # every known category, verbose
kdebugsettings --disable-full-debug   # every known category, silent
```

## Severity levels

A category is not an on/off switch. Picking a level enables that
severity and everything more serious:

| Level      | Messages printed                    |
| ---------- | ----------------------------------- |
| Full Debug | debug, info, warning, critical      |
| Info       | info, warning, critical             |
| Warning    | warning, critical                   |
| Critical   | critical only                       |
| Off        | nothing                             |

Each level is written out explicitly for all four severities, so a
category has a defined state whatever the system defaults are. Choosing
*Warning* for `org.kde.example` produces:

```ini
[Rules]
org.kde.example.info=false
org.kde.example.debug=false
org.kde.example.warning=true
org.kde.example.critical=true
```

Only categories that differ from their default severity are written to
`qtlogging.ini`, which keeps the file short and lets applications change
their own defaults later.

## The three tabs

- **KDE Application** — every category declared by an installed
  `.categories` file. **Restore Defaults** puts them all back to the
  severity their own application declared.
- **Custom Rules** — categories KDebugSettings knows nothing about,
  typically from a third party application or from code you are
  currently writing. The name accepts a `*` wildcard at the start, at
  the end or both, so `org.kde.pim.*` covers all of PIM at once.
- **Rules Settings With Environment Variable** — read-only view of
  `QT_LOGGING_RULES`, which Qt applies *after* `qtlogging.ini` and which
  therefore wins over everything configured here. Useful when a category
  stubbornly refuses to behave as the first two tabs say it should.

A rule whose category is just `*`, that is `*=true` or `*=false`,
overrides all the other rules. KDebugSettings shows a warning when it
finds one. If you really want a catch-all, write `*.*=true` instead: it
is ordered so that more specific rules still win.

## Saving rule sets

**OK** and **Apply** write to `qtlogging.ini`. To keep several rule sets
side by side, one per bug you are chasing:

- **Save As → Save As Group** stores them under
  `~/.local/share/kdebugsettings/groups/`, ready to be picked again from
  **Load → Load Group**. **Load → Manage Group** renames, removes and
  exports them.
- **Save As → Save As File** exports a `.kdebugsettingsrules` file
  anywhere on disk; **Load → Load From File** reads it back.

Unlike **Apply**, both write out *every* category, so that reloading
restores exactly the state you saved. Loading only fills the dialog —
press **OK** or **Apply** to activate the rules.

## Declaring your categories

The **KDE Application** list is not hardcoded: it comes from the
`.categories` files installed by applications, looked up in

- `/usr/share/qlogging-categories6/`, where `kde.categories` holds the
  categories of the KDE applications,
- the XDG configuration directories, for example `~/.config/`,
- `$XDG_CONFIG_HOME/qdebug.categories/`, for applications outside KDE.

One category per line, `#` starts a comment:

```text
<category> <description> [DEFAULT_SEVERITY [<severity>]] [IDENTIFIER [<id>]]
```

Name and description are mandatory, the rest is optional. `<severity>`
is `DEBUG`, `INFO`, `WARNING` or `CRITICAL` and is the level **Restore
Defaults** returns to (`INFO` when absent). `<id>` is the name of the
`QLoggingCategory` object in the source, which makes the category
searchable by the name developers actually type:

```text
org.kde.example Example core DEFAULT_SEVERITY [WARNING] IDENTIFIER [EXAMPLE_LOG]
```

With extra-cmake-modules you do not write that file by hand. Declare the
category and install the generated file:

```cmake
ecm_qt_declare_logging_category(example
    HEADER example_debug.h
    IDENTIFIER EXAMPLE_LOG
    CATEGORY_NAME org.kde.example
    DESCRIPTION "Example core"
    DEFAULT_SEVERITY Warning
    EXPORT EXAMPLE
)
ecm_qt_install_logging_categories(EXPORT EXAMPLE
    FILE example.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)
```

If the application is not installed system wide — one you are building
yourself, say — point **Insert…** at its `.categories` file to add its
categories to the list for this session.

When you rename a category, ship a `.renamecategories` file next to the
`.categories` one so that the rules users already have keep working:

```text
# old module name<space>new module name
org.kde.old.name org.kde.new.name
```

## System Settings module

The same three tabs are available in System Settings, under *System
Administration → Debug Settings*, writing the same `qtlogging.ini`.

## Building

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build
```

Requires Qt 6, KDE Frameworks 6 and extra-cmake-modules; see
`CMakeLists.txt` for the exact minimum versions. The handbook is built
when KF6DocTools is found.

## Links

- Bug reports:
  <https://bugs.kde.org/enter_bug.cgi?product=kdebugsettings>
- Source: <https://invent.kde.org/utilities/kdebugsettings>
- Handbook: `help:/kdebugsettings`, or the **Help** button of the dialog

## License

The source code is LGPL-2.0-or-later, the build files are BSD-3-Clause
and the handbook is GFDL-1.2-or-later; the combined program is
distributed under the GPL-2.0-only. Every file carries its own SPDX
header, and the license texts are in the `LICENSES` directory.
