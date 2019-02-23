const knex = require('knex')(require('./knexfile'));

const bookshelf = require('bookshelf')(knex);

export { bookshelf, knex };
export default knex;
