const fs = require('fs');
const dot = require('./dot');

const draw = (drawCommands, cameraCommands) => {
    //
    // write your code in here.
    //
    let id = 0;
    for(let x=-10; x<10; x++) {
        for(let y=-10; y<10; y++) {
            drawCommands.push(
                dot.dot(id, {x, y, z: 0}, {x: 1, y: 1, z: 1}, {x: 1, y: 1, z: 0})
            );
            id++;
        }
    }
    cameraCommands.push(dot.sleep(10.0));
    cameraCommands.push(dot.cameraTranslate({x: 0.5, y: 0, z: 0}));
}

const main = () => {
    const drawCommands = [];
    const cameraCommands = [];
    draw(drawCommands, cameraCommands);
    console.log('update')
    return JSON.stringify(
        {
            "queues": [
                {
                    commands: drawCommands
                },
                {
                    commands: cameraCommands
                }
            ]
        }
    , null, "\t");
}

fs.writeFileSync("../bin/data/dot.json", main());
module.exports = { main }