const express = require('express');

const router = express.Router();

module.exports = router;
const roomModel = require("../mudels/rooms_M");

/*router.get('/saveDummy', (req,res) =>{
    const modeldata = new roomModel({
        room_number: 15,
        bed_number:1,
        dayar_name: "gal",
    });
    modeldata.save();
    res.send("hi");
});*/

router.get('/Add', (req, res) => {
    res.render("roomAdd", { pageTitle: "הוספת חדר", item: {}});
});

router.post('/Add', (req,res) => {
    const {room_number, bed_number, dayar_name, device_number} = req.body;
    const modeldata = new roomModel({
        room_number: room_number,
        bed_number: bed_number,
        dayar_name: dayar_name,
        device_number: device_number
    });
    modeldata.save();
    res.redirect('/R/List');
});

router.get('/List', async (req, res) => {
    const room_data = await roomModel.find();
    res.render("roomList", { pageTitle: "ניהול חדרים", data: room_data });
});

router.get('/Edit', async (req, res) => {
    const item_data = await roomModel.findById(req.query.id);
    res.render("roomAdd", { pageTitle: "עריכת חדר", item: item_data });
});

router.post('/Edit', async (req, res) => {
    const {room_number, bed_number, dayar_name, device_number} = req.body;
    const modeldata = {
        room_number: room_number,
        bed_number: bed_number,
        dayar_name: dayar_name,
        device_number: device_number
    };
    const item_data = await roomModel.findByIdAndUpdate(req.query.id, modeldata);
    res.redirect('/R/List');
});

router.post('/Delete', async (req, res) => {
    const { id } = req.body;
    const item_data = await roomModel.findByIdAndDelete(id);
    res.redirect('/R/List');
});

