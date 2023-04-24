const  mongoose = require('mongoose');

const dataSchema = new mongoose.Schema({
    room_number:{
        required: true,
        type: Number
    },
    bed_number:{
        required: true,
        type: Number
    },
    dayar_name:{
        required: false,
        type: String
    },
    device_number:{
        required: false,
        type: Number
    },
    CallIsActive:{
        required: false,
        type: Number
    }
});

module.exports = mongoose.model('alarmer_rooms', dataSchema);