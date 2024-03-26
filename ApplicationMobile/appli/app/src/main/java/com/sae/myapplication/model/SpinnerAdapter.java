package com.sae.myapplication.model;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sae.myapplication.R;

import java.util.List;

/**
 * ArrayAdapter personnalisé pour afficher une liste déroulante avec du texte et des images.
 */
public class SpinnerAdapter extends ArrayAdapter<String> {

    private Context context;
    private List<String> statesList;

    /**
     * Constructeur de SpinnerAdapter.
     *
     * @param context    Le contexte de l'activité appelante.
     * @param states     Liste des abréviations d'État à afficher dans la liste déroulante.
     */
    public SpinnerAdapter(Context context, List<String> states) {
        super(context, R.layout.my_selected_item, states);
        this.context = context;
        this.statesList = states;
    }

    /**
     * Remplace la méthode pour retourner une vue personnalisée pour chaque élément de la liste déroulante.
     *
     * @param position       La position de l'élément dans l'ensemble de données de l'adaptateur.
     * @param convertView    L'ancienne vue à réutiliser, si possible.
     * @param parent         Le parent auquel cette vue sera éventuellement attachée.
     * @return               La vue correspondant aux données à la position spécifiée.
     */
    @Override
    public View getDropDownView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        return getCustomView(position, convertView, parent);
    }

    /**
     * Remplace la méthode pour retourner une vue personnalisée pour l'élément sélectionné dans la liste déroulante.
     *
     * @param position       La position de l'élément dans l'ensemble de données de l'adaptateur.
     * @param convertView    L'ancienne vue à réutiliser, si possible.
     * @param parent         Le parent auquel cette vue sera éventuellement attachée.
     * @return               La vue correspondant aux données à la position spécifiée.
     */
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        return getCustomView(position, convertView, parent);
    }

    /**
     * Retourne une vue personnalisée pour l'élément de la liste déroulante.
     *
     * @param position       La position de l'élément dans l'ensemble de données de l'adaptateur.
     * @param convertView    L'ancienne vue à réutiliser, si possible.
     * @param parent         Le parent auquel cette vue sera éventuellement attachée.
     * @return               La vue personnalisée avec à la fois une image et du texte.
     */
    public View getCustomView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View row = inflater.inflate(R.layout.my_dropdown_item, parent, false);

        TextView state = row.findViewById(R.id.text);
        ImageView flag = row.findViewById(R.id.img);

        Resources res = context.getResources();
        String drawableName = statesList.get(position).toLowerCase();
        int resId = res.getIdentifier(drawableName, "drawable", context.getPackageName());
        Drawable drawable = res.getDrawable(resId);

        state.setText(statesList.get(position));
        flag.setImageDrawable(drawable);

        return row;
    }
}
