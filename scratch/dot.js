const lerp = require('lerp');

const sleep = (s) => {
    return {
        name: "sleep",
        s
    };
}
const position = (id, position) => {
    return {
        name: "position",
        id,
        position
    }
};
const scale = (id, scale) => {
    return {
        name: "scale",
        id,
        scale
    }
};
const color = (id, color) => {
    return {
        name: "color",
        id,
        color
    }
};
const dot = (id, position, scale, color) => {
    return {
        id,
        position,
        scale,
        color,
        name: "dot"
    };
};
const lerpTo = (id, from, to, duration, fn) => {
    const list = [];
    const obj = {
        name: "list",
        list
    };
    list.push(fn(id,from))
    for(let i=0; i<100; i++) {
        list.push(sleep(duration/100));
        const x = lerp(from.x, to.x, i/100);
        const y = lerp(from.y, to.y, i/100);
        const z = lerp(from.z, to.z, i/100);
        list.push(fn(id, { x, y, z }));
    }
    list.push(fn(id,to));
    return obj;
};
const moveTo = (id, from, to, duration) => lerpTo(id, from, to, duration, position);
const scaleTo = (id, from, to, duration) => lerpTo(id, from, to, duration, scale);
const colorTo = (id, from, to, duration) => lerpTo(id, from, to, duration, color);
const parallel = (list) => {
    return {
        name: "parallel",
        list
    };
};
module.exports = {
    sleep,
    position,
    scale,
    color,
    dot,
    moveTo,
    scaleTo,
    colorTo,
    parallel
};