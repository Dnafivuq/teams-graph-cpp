# Build

To build the project run:

    cmake -B build
    cmake --build build

The compiled executable can be found at `./build/app/teams_cli`.

# Documentation

The project uses doxygen for documentation.
To generate the documentation run:

    doxygen

The documentation can be found at `./html/index.html` and can be opened with a browser.

# Commands

The project contains application that, executable is `./build/app/teams_cli`, that offers commands interacting with MS Teams.

List of those commends:

## Team

## Channel

## Post

## Member

## Chat

## Group

This is a command for managing groups of user definied by the app user (not a part of MS Teams).

Each group contains name of the group and members (list of email adresses of users belonging to the group).

Groups are locally stored.

### add, a

Adds a new group.

Arguments:

- -n, --name

  Name of the group. Has to be unique. Is required.

- -m, --members

  List of email adresses of group members. Is required.

  Can be given using one flag and list of strings, e.g. `-m "1@gmail.m" "2@email.a"`

  or using multiple flags, e.g. `-m "1@gmail.m" -m "2@email.a"`

### remove, r

Removes a group.

Arguments:

- -g, --group

  Name of the group. Is required.

### list, ls

Lists all defined groups.

Takes no arguments.

### show, sh

Displays contents (name and members) of a group.

Arguments:

- -g, --group

  Name of the group. Is required.

### send, s

Sends message to members of a group.

Arguments:

- msg

  Content of the message

- -g, --group

  Name of the group. Is required.

## Template

This is a command for managing templates definied by the app user (not a part of MS Teams).

Each template contains name and text.
In text user can define variables by adding `[]` in place where variable is supposed to be.
Variables do not require names.

Templates are stored locally.

### add, a

Adds a new template.

Arguments:

- -n, --name

  Name of the template. Has to be unique. Is required.

- -t, --text

  Text of the template with optional variables. Is required.

### remove, r

Removes a template.

Arguments:

- -t, --template

  Name of the group. Is required.

### list, ls

Lists all defined templates.

Takes no arguments.

### show, sh

Displays contents (name and text) of a template.

Arguments:

- -t, --template

  Name of the tempate. Is required.

### send, s

Sends message, template text with variables filled with values, to members of a group.

Arguments:

- -t, --template

  Name of the tempate. Is required.

- -g, --group

  Name of the group. Is required.

- -v, --variables

  List of values to fill the variables in the text.

  Number of given values must be equal to number_of_variables_in_text \* number_of_members_in_the_group.

  Values must be specified using multiple flags, e.g. `-v "b" -v "a"`.

  Order of specifing values is important - this command expects values for all variables in the text for one user in a row and like that for every user. Values will replace variables in order of being specified.
