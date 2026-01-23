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

Each group contains name of the group and members (list of users belonging to the group).

The groups are locally stored.

### add

Adds a new group.

Arguments:

- -n, --name

  Name of the group. Has to be unique. Is required.

- -m, --members

  List of email adresses of group members. Is required.

  Can be given using one flag and list of strings, e.g. `-m "1@gmail.m" "2@email.a"`

  or using multiple flags, e.g. `-m "1@gmail.m" -m "2@email.a"`

### remove

Removes a group.

Arguments:

- -g, --group

  Name of the group. Is required.

### list

Lists all defined groups.

Takes no arguments.

### show

Displays contents (name and members) of a group.

Arguments:

- -g, --group

  Name of the group. Is required.

### send

Sends message to members of a group.

Arguments:

- msg

  Content of the message

- -g, --group

  Name of the group. Is required.

## Template

### add

### remove

### list

### show

### send
