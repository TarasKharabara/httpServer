# Start Here

1. Use this template repository to create a private fork (click the green `Use this template` button and not the `Fork` button).
1. Follow the instructions in `INSTRUCTIONS.md`.
1. Give [@tes-mersive](https://github.com/tes-mersive) (`estephens@mersive.com`) collaborator access when complete.
1. Inform your Mersive contact that the assignment is complete.

# Your Documentation

## HTTP basic server
Basic http server which support PUT, GET and DELETE commands

## Installation
gcc 11 was used for compilation, please be sure that you are using the same

cd ./serverHTTP
mkdir build
cd ./build
cmake ..
make

As a result "serverHTTP" binary file should appear inside of build folder 

## Usage
To store data:
curl -i -H "Content-Type: application/json" -X POST -d '{ "secret": 9898 }' http://localhost:8000/foo

To delete data:
curl -i -X DELETE http://localhost:8000/foo 

Get data from server:
curl -i http://localhost:8000/foo


## Usage
Possible improvement:
* As for me it mind be good to implement thread pool functionality for parallel request handling.
* Implement response generator(do not use hardcoded values).
* Add unit test coverage.
* Keep client data somewhere in database or file.
