const TABLE_NAME = 'sensor_luz';

exports.up = async (db) => {
  await db.schema.createTable(TABLE_NAME, (table) => {
    table.increments(`${TABLE_NAME}_id`);
    table.decimal('lux', 6,2).notNullable();
    table.timestamp('criado_em').notNullable().defaultTo(db.fn.now());
    table.timestamp('atualizado_em').notNullable().defaultTo(db.fn.now());
    table.charset('utf8');
    table.engine('InnoDB');
  });
};

exports.down = db => db.schema.dropTable(TABLE_NAME);

exports.configuration = { transaction: true };
