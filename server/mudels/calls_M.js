const mongoose = require('mongoose');

const callsDB = mongoose.Schema({
    room_number: {
        require: true,
        type: Number
    },
    bed_number: {
        require: true,
        type: Number
    },
    Opening_call_hour:{
        require: true,
        type: String
    },
    closs_call_hour: {
        require: false,
        type: String
    }
});

module.exports = mongoose.model('readability', callsDB);