const lerp = require('lerp');
// utility functions
/**
 * 指定秒数待機します。
 * @param {number} s 
 */
const sleep = (s) => {
    return {
        name: "sleep",
        s
    };
}
// draw functions
/**
 * 指定の球体の位置を設定します。
 * @param {number} id 球体のID
 * @param {Object} position 球体の位置
 */
const position = (id, position) => {
    return {
        name: "position",
        id,
        position
    }
};
/**
 * 指定の球体のスケールを設定します。
 * @param {number} id 球体のID
 * @param {Object} scale 球体のスケール
 */
const scale = (id, scale) => {
    return {
        name: "scale",
        id,
        scale
    }
};
/**
 * 指定の球体の色を設定します。
 * @param {number}} id 球体のID
 * @param {Object} color 球体の色(0~1, 0~1, 0~1)
 */
const color = (id, color) => {
    return {
        name: "color",
        id,
        color
    }
};
/**
 * 指定の球体の位置,スケール,色を設定します。
 * @param {number} id 球体のID
 * @param {Object} position 球体の位置
 * @param {Object} scale 球体のスケール
 * @param {Object} color 球体の色(0~1, 0~1, 0~1)
 */
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
/**
 * 指定の球体を指定位置まで指定の時間で移動します。
 * @param {number} id 球体のID
 * @param {Object} from 開始位置
 * @param {Object} to 終了位置
 * @param {number} duration 時間(s)
 */
const moveTo = (id, from, to, duration) => lerpTo(id, from, to, duration, position);
/**
 * 指定の球体を指定スケールまで指定の時間で遷移します。
 * @param {number} id 球体のID
 * @param {Object} from 開始スケール
 * @param {Object} to 終了スケール
 * @param {number} duration 時間(s)
 */
const scaleTo = (id, from, to, duration) => lerpTo(id, from, to, duration, scale);
/**
 * 指定の球体を指定色まで指定の時間で遷移します。
 * @param {number} id 球体のID
 * @param {Object} from 開始色
 * @param {Object} to 終了色
 * @param {number} duration 時間(s)
 */
const colorTo = (id, from, to, duration) => lerpTo(id, from, to, duration, color);
/**
 * 引数のコマンドを並列で実行するコマンドを作成します。
 * @param {Array} list コマンドのリスト
 */
const parallel = (list) => {
    return {
        name: "parallel",
        list
    };
};
// camera functions
/**
 * カメラを指定の位置に設定します。
 * @param {Object} position カメラの位置
 */
const cameraPosition = (position) => {
    return {
        name: "cameraPosition",
        position
    };
};
/**
 * カメラの注視点を指定の位置に設定します。
 * @param {Object} position カメラの注視点
 */
const cameraLookAt = (position) => {
    return {
        name: "cameraLookAt",
        position
    };
};
/**
 * カメラを指定のオフセットだけ移動します。
 * @param {Object} offset オフセット
 */
const cameraTranslate = (offset) => {
    return {
        name: "cameraTranslate",
        offset
    };
};
/**
 * カメラを指定方向に回転します。
 * @param {Object} v 回転軸
 * @param {number} radian 回転量(radian)
 */
const cameraRotateD = (v, radian) => {
    radian = radian * (3.14 / 180.0);
    return {
        name: "cameraRotate",
        point: { x: v.x, y: v.y, z: v.z },
        radian
    };
};
/**
 * カメラを指定方向に回転します。
 * @param {Object} v 回転軸
 * @param {number} radian 回転量(degree)
 */
const cameraRotateR = (v, radian) => {
    return {
        name: "cameraRotate",
        point: { x: v.x, y: v.y, z: v.z },
        radian
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
    parallel,
    cameraPosition,
    cameraLookAt,
    cameraTranslate,
    cameraRotateD,
    cameraRotateR,
};