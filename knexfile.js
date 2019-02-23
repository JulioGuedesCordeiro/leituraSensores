module.exports = {
  client: 'mysql',
  connection: {
    host: 'localhost',
    database: 'smartcity',
    user: 'root',
    password: '',
    insecureAuth: true
  },
  pool: {
    min: 2,
    max: 10
  },
  migrations: {
    tableName: 'migrations',
    directory: './migrations'
  }
};

