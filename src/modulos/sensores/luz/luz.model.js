import { bookshelf } from '../../../../bookshelf';

const SensorLuz = bookshelf.Model.extend({
  tableName: 'sensor_luz',
  idAttribute: 'sensor_luz_id',
  hasTimestamps: ['criado_em', 'atualizado_em'],
},  {
    listar(page = 0, pageSize = 10, pesquisa = '') {
      const query = this
        .query((luz) => {
          luz.where('lux', 'LIKE', `%${pesquisa}%`);
        });
      if (page) {
        return query.fetchPage({ page, pageSize });
      }
      return query.fetchAll();
    },
    salvar(lux) {
      this.forge({lux}).save();
    }
  });

export default SensorLuz;
