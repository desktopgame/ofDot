const fs = require('fs');
const dot = require('./dot');

const draw = (commands) => {
    //
    // write your code in here.
    //
    let id = 0;
    for(let x=-10; x<10; x++) {
        for(let y=-10; y<10; y++) {
            commands.push(
                dot.dot(id, {x, y, z: 0}, {x: 1, y: 1, z: 1}, {x: 1, y: 1, z: 0})
            );
            id++;
        }
    }
}

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

fs.writeFileSync("../bin/data/dot.json", main());
module.exports = { main }