import abc
import argparse
import copy
import functools
import json


def row_to_matrix(row, nkeys_per_row):
  """Convert keymap definition in a row to a matrix for easier indexing.

  Args:
    row: a list of key definitions.
    ncols_per_row: a list of numbers indicating number of keys in each
      row. The sum should add to the length of `row`.
  """
  assert sum(nkeys_per_row) == len(row)
  matrix = []
  idx = 0
  for nkeys in nkeys_per_row:
    matrix.append([row[idx + i] for i in range(nkeys)])
    idx += nkeys
  return matrix


class Keymap(abc.ABC):

  def __init__(self, input_keymap):
    """Init keymap from input_keymap.

    Args:
      input_keymap: a json dict exported from QMK configurator.
    """
    self.verify_input_keymap(input_keymap)
    self.layers = self.convert_layers(input_keymap)

  @abc.abstractmethod
  def verify_input_keymap(self, input_keymap):
    """Verify the input keymap is what we need."""

  @abc.abstractmethod
  def convert_layer(self, layer):
    """Convert one layer of keymap from input keymap to my layout."""

  def convert_layers(self, layers):
    """Convert all layers by default."""
    return [self.convert_layer(layer) 
            for layer in layers['layers']]

  @property
  @abc.abstractmethod
  def qmk_meta(self):
    """Get meta info used for exporting to QMK configurator."""

  def to_qmk_configurator(self):
    """Export to QMK configurator json format."""
    meta = copy.deepcopy(self.qmk_meta)
    meta['layers'] = self.layers

    return json.dumps(meta, indent=2)


class Ortho4x12(Keymap):
  """Base class for all keymap that import from 4x12 layout."""

  def verify_input_keymap(self, input_keymap):
    # We expect to load from a keymap defined for planck/rev6
    # and with grid layout (4x12)
    assert input_keymap['keyboard'] == 'planck/rev6'
    assert input_keymap['layout'] == 'LAYOUT_planck_grid'

  def row_to_matrix(self, layer):
    return row_to_matrix(layer, nkeys_per_row=[12] * 4)

  def matrix_to_row(self, matrix):
    return sum(matrix, [])


class PlanckKeymap(Ortho4x12):

  def __init__(self, input_keymap, device='planck/rev6', layout='mit'):
    self.device = device
    self.layout = layout

    assert device in ['planck/rev6', 'planck/ez']
    if device == 'planck/ez':
      assert layout == 'mit'

    super().__init__(input_keymap)

  def convert_layer(self, layer):
    matrix = self.row_to_matrix(layer)
    if self.layout == 'grid':
      # no conversion is needed
      pass
    elif self.layout == 'mit':
      # a 2U space, we discard the key on the left-space
      del matrix[3][5]
    else:
      raise KeyError(f'Unsupported planck layout: {self.layout}')

    return self.matrix_to_row(matrix)

  @property
  def qmk_meta(self):
    return dict(
        keyboard=self.device,
        keymap=f'custom_planck_rev6_{self.layout}',
        layout=f'LAYOUT_planck_{self.layout}'
    )


class CorneKeymap(Ortho4x12):

  def convert_layer(self, layer):
    # We map the planck grid in the bottom row
    #   K0, K1, Opt, Cmd, Lwr, Spc, Spc, Rsr, Lft, Dwn, Up, Rgt
    # to the following 6 keys:
    #                Cmd, Lwr, Spc, Spc, Rsr, Opt
    matrix = self.row_to_matrix(layer)
    matrix[3] = [matrix[3][i] for i in [3, 4, 5, 6, 7, 2]]
    return self.matrix_to_row(matrix)

  @property
  def qmk_meta(self):
    return dict(
        keyboard='crkbd/rev1/legacy',
        keymap='custom_corne',
        layout='LAYOUT_split_3x6_3'
    )


class Reviung41Keymap(Ortho4x12):

  def convert_layer(self, layer):
    # We map the planck grid in the bottom row
    #   K0, K1, Opt, Cmd, Lwr, Spc1, Sp2, Rsr, Lft, Dwn, Up, Rgt
    # to the following 5 keys (right space is kept):
    #                Cmd, Lwr, Spc2, Rsr, Opt
    matrix = self.row_to_matrix(layer)
    matrix[3] = [matrix[3][i] for i in [3, 4, 6, 7, 2]]
    return self.matrix_to_row(matrix)

  @property
  def qmk_meta(self):
    return dict(
        keyboard='reviung41',
        keymap='custom_reviung41',
        layout='LAYOUT_reviung41'
    )


def main():
  keyboards = dict(
      planck_mit=functools.partial(PlanckKeymap, layout='mit'),
      planck_grid=functools.partial(PlanckKeymap, layout='grid'),
      planck_ez=functools.partial(PlanckKeymap, 
                                  layout='mit', device='planck/ez'),
      corne=CorneKeymap,
      reviung41=Reviung41Keymap,
  )

  parser = argparse.ArgumentParser('Keymap converter.')
  parser.add_argument('input_json',
                      help='json file exported from QMK Configurator.')
  parser.add_argument('keyboard', help='Target keyboard name.',
                      choices=keyboards.keys())
  parser.add_argument('export_type', choices=['qmk'],
                      help='Export type.')

  args = parser.parse_args()
  with open(args.input_json, 'r') as in_f:
    input_keymap = json.load(in_f)
  keymap = keyboards[args.keyboard](input_keymap)

  if args.export_type == 'qmk':
    print(keymap.to_qmk_configurator())


if __name__ == '__main__':
  main()
