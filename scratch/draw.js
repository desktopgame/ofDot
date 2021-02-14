const fs = require('fs');
const dots = require('./dots');
//
// write your code in below.
//
const draw = (commands) => {
    let id = 0;
    for(let x=-10; x<10; x++) {
        for(let y=-10; y<10; y++) {
            commands.push(
                dots.dot(id, {x, y, z: 0}, {x: 1, y: 1, z: 1}, {x: 0.1, y: 0.1, z: 1})
            );
            id++;
        }
    }
}
//
// update json
//
const main = () => {
    const commands = [];
    draw(commands)
    console.log('update')
    return JSON.stringify(
        {
            "queues": [
                {
                    commands
                }
            ]
        }
    , null, "\t");
}
fs.writeFileSync("../bin/data/dots.json", main());
//
// modules
//
module.exports = { main }