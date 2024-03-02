const express = require('express');
const app = express();
const port = 3000;

// 车辆数据
const vehicles = [
  { id: 1, make: 'Toyota', model: 'Camry' },
  { id: 2, make: 'Honda', model: 'Accord' },
  { id: 3, make: 'Ford', model: 'Mustang' }
];

// 路由：获取所有车辆
app.get('/api/vehicles', (req, res) => {
  res.json(vehicles);
});

app.get('/', (req, res) => {
    res.send('Hello, World!');
  });

// 启动服务器
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});