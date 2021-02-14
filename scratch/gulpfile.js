const gulp = require('gulp');
const gutil = require('gulp-util');
const decache = require('decache');

function string_src(filename, string) {
    var src = require('stream').Readable({ objectMode: true })
    src._read = function () {
      this.push(new gutil.File({
        cwd: "",
        base: "",
        path: filename,
        contents: new Buffer(string)
      }))
      this.push(null)
    }
    return src
}
gulp.task('reload', (done) => {
    decache('./draw');
    let draw = require('./draw')
    const ret = string_src("dot.json", draw.main())
      .pipe(gulp.dest('../bin/data/'));
    done();
    draw = null;
    return ret;
});
gulp.task('default', () => {
    gulp.watch('*.js', gulp.task('reload'));
});