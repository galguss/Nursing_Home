const express = require('express');
const router = express();

/*const callsDB = require('../mudels/calls_M');
const rooms_M = require('../mudels/rooms_M');*/



router.get('/Add', (req, res) => {
    res.render("callAdd", { pageTitle: "הוספת קריאה", item: {}});
});



module.exports = router;